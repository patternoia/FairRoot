/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "FairGenericParDbIo.h"
#include "FairParSet.h"

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
  fName = "FairGenericParIo";
}

Bool_t FairGenericParDbIo::init(FairParSet* pPar)
{
  return read(pPar);
}

void FairGenericParDbIo::SetServerURI(std::string value) {
  TGenBase::Client::Instance()->SetServerURI(value);
}
void FairGenericParDbIo::SetAccessToken(std::string value) {
  TGenBase::Client::Instance()->SetAccessToken(value);
}
void FairGenericParDbIo::SetVerbose(bool value) {
  TGenBase::Client::Instance()->SetVerbose(value);
}


Bool_t FairGenericParDbIo::read(FairParSet *pPar) {
  // Text_t *name = const_cast<char*>(pPar->GetName());
  Int_t version = pPar->getInputVersion(inputNumber);

  // does not exist yet
  if (version <= 0) {
    pPar->setInputVersion(-1, inputNumber);
    return kFALSE;
  }

  // prevent re-read
  if (pPar->getInputVersion(inputNumber) == version &&
      pPar->getInputVersion(inputNumber) != -1) {
    return kTRUE;
  }

  if (!pPar) {
    pPar->setInputVersion(-1, inputNumber);
    return kFALSE;
  }

  std::vector<TGenBase::ObjectStore> result = TGenBase::QueryBuilder().Where("Name", "=", pPar->GetName())
    .OrderBy("CreatedAt", "desc")
    // add more filtering
    .Execute<TGenBase::ObjectStore>();
  // std::vector<TGenBase::ObjectStore> result = TGenBase::ObjectStore::GetByName(pPar->GetName());

  // not found in DB
  if (!result.size()) {
    pPar->setInputVersion(-1, inputNumber);
    return kFALSE;
  }

  FairParSet *clone = static_cast<FairParSet*>(pPar->Clone());
  for (auto object : result) {
    TGenBase::Streamer ParameterStreamer(object.GetObject());
    if (ParameterStreamer.AsString().size())
    {

      ParameterStreamer.Fill(clone);

      // change condition
      if (clone->GetName() != 0) {
        pPar->clear();
        ParameterStreamer.Fill(pPar);
        pPar->setChanged();
        std::cout << "Container " << pPar->GetName() << " initialized from DB." << std::endl;

        delete clone;
        return kTRUE;
      }
    }
  }

  delete clone;
  return kFALSE;
}

Int_t FairGenericParDbIo::write(FairParSet *pPar) {
  if (!pPar) return -1;

  const auto version = pPar->getInputVersion(inputNumber);
  pPar->setInputVersion(version+1, inputNumber);

  TGenBase::ObjectStore par;
  par.SetName(pPar->GetName());
  // TGenBase::Streamer ParameterStreamer(static_cast<TObject*>(pPar));
  TGenBase::Streamer ParameterStreamer(pPar);
  par.SetObject(ParameterStreamer.AsString());
  par.Store();

  return ParameterStreamer.AsString().size() / 2;
}
