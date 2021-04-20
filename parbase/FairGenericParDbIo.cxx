/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "FairGenericParDbIo.h"
#include "FairParSet.h"
#include "FairRuntimeDb.h"
#include "FairRtdbRun.h"
#include "FairParDbIo.h"

#include "TClass.h"

#pragma GCC diagnostic push 
#pragma GCC diagnostic ignored "-Wshadow"

#include "TGenBase/Client.h"
#include "TGenBase/ObjectStore.h"
#include "TGenBase/Streamer.h"
#include "TGenBase/QueryBuilder.h"

#pragma GCC diagnostic pop

ClassImp(FairGenericParDbIo)

FairGenericParDbIo::FairGenericParDbIo(FairParDbIo* parIo)
  : FairDetParIo()
{
  fParIo = parIo;
  fName = "FairGenericParIo"; // Do not ever change
}

Bool_t FairGenericParDbIo::init(FairParSet* pPar)
{
  return read(pPar);
}

Bool_t FairGenericParDbIo::read(FairParSet *pPar) {
  std::cout << "FairGenericParDbIo::read " << pPar->GetName() << std::endl;
  if (!pPar) {
    return kFALSE;
  }

  Int_t version = pPar->getInputVersion(inputNumber);

  // look up versions set with rtdb->setInputVersion
  FairParVersion *currVers =
      FairRuntimeDb::instance()->getCurrentRun()->getParVersion(pPar->GetName());
  Int_t v = currVers->getInputVersion(inputNumber);
  std::cout << v << std::endl;
  if (v > 0) {
    version = v;
  }

  // prevent re-read
  if (pPar->getInputVersion(inputNumber) == version &&
      pPar->getInputVersion(inputNumber) != -1) {
    return kTRUE;
  }

  const UInt_t runId = FairRuntimeDb::instance()->getCurrentRun()->getRunId();

  // prepare query
  std::vector<TGenBase::ObjectStore> result = TGenBase::QueryBuilder()
    .Where("Name", "=", pPar->GetName())
    .Where("Metadata->Author", "=", pPar->getAuthor())
    .Where("Metadata->ClassName", "=", pPar->IsA()->GetName())
    .Where("Metadata->Context", "=", pPar->getParamContext())
    .Where("Metadata->Version", "<=", std::to_string(version))
    .Where("Metadata->RunId", "<=", std::to_string(runId))
    .OrderBy("CreatedAt", "desc")
    .OrderBy("Metadata->Version", "desc")
    .OrderBy("Metadata->RunId", "desc")
    .Last()
    .Execute<TGenBase::ObjectStore>();

  // not found in DB
  if (!result.size()) {
    pPar->setInputVersion(-1, inputNumber);
    return kFALSE;
  }

  const auto& object = result[0];
  TGenBase::Streamer ParameterStreamer(object.GetObject());
  if (ParameterStreamer.AsString().size())
  {
    auto metadata = object.GetMetadata();

    if (std::string(pPar->IsA()->GetName()) != metadata["ClassName"]) {
      std::cout << "FairGenericParDbIo: Container class mismatch: "
        << pPar->GetName()
        << " expected. "
        << metadata["ClassName"]
        << " found in DB."
        << std::endl;
      assert(false);
    }

    ParameterStreamer.Fill(pPar);
    pPar->setChanged();

    pPar->setInputVersion(std::stoi(metadata["Version"]), inputNumber);
    // pPar->setAuthor(metadata["Author"].c_str());
    // pPar->setContext(metadata["Context"].c_str());
    // pPar->setRunId(std::stoi(metadata["RunId"]));

    std::cout << "Container " << pPar->GetName() << " initialized from DB." << std::endl;

    return kTRUE;
  }

  return kFALSE;
}

Int_t FairGenericParDbIo::write(FairParSet *pPar) {
  if (!pPar) return -1;

  const UInt_t runId = FairRuntimeDb::instance()->getCurrentRun()->getRunId();

  Int_t version = pPar->getInputVersion(inputNumber);
  version = version > 0 ? version + 1 : 1;
  pPar->setInputVersion(version, inputNumber);

  TGenBase::ObjectStore object;
  object.SetName(pPar->GetName());

  TGenBase::Streamer ParameterStreamer(pPar);
  object.SetObject(ParameterStreamer.AsString());

  std::map<std::string, std::string> metadata{{
    { "Author", pPar->getAuthor() },
    { "ClassName", pPar->IsA()->GetName() },
    { "Context", pPar->getParamContext() },
    { "Version", std::to_string(version) },
    { "RunId", std::to_string(runId) }
  }};
  object.SetMetadata(metadata);

  object.Store();

  return ParameterStreamer.AsString().size() / 2;
}
