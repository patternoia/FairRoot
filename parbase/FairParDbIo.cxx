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
  std::cout << "FairParDbIo::print()" << std::endl;
}

void FairParDbIo::readVersions(FairRtdbRun* currentRun)
{
}
