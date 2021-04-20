/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "FairParDbIo.h"
#include "FairRtdbRun.h"
#include "FairRuntimeDb.h"
#include "FairGenericParDbIo.h"

#pragma GCC diagnostic push 
#pragma GCC diagnostic ignored "-Wshadow"
#include "TGenBase/Client.h"
#pragma GCC diagnostic pop


#include <iostream>

ClassImp(FairParDbIo)

FairParDbIo::FairParDbIo()
  : FairParIo()
{
  FairRuntimeDb::instance()->activateParIo(this);
}

FairParDbIo::~FairParDbIo()
{
  close();
}

void FairParDbIo::close()
{
}

void FairParDbIo::print()
{
  std::cout << "FairParDbIo" << std::endl;
}

void FairParDbIo::readVersions(FairRtdbRun* currentRun)
{
  std::cout << "FairParDbIo::readVersions()" << std::endl;
  fRunId = currentRun->getRunId();
}

void FairParDbIo::SetServerURI(std::string value) {
  TGenBase::Client::Instance()->SetServerURI(value);
}
void FairParDbIo::SetAccessToken(std::string value) {
  TGenBase::Client::Instance()->SetAccessToken(value);
}
void FairParDbIo::SetVerbose(bool value) {
  TGenBase::Client::Instance()->SetVerbose(value);
}
