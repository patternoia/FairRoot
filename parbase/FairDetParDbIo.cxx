/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "FairDetParDbIo.h"

#include "FairParSet.h"
#include <iostream>

ClassImp(FairDetParDbIo)

FairDetParDbIo::FairDetParDbIo(FairParDbIo* parIo)
    : FairDetParIo(), fParIo(parIo) {
}

Bool_t FairDetParDbIo::read(FairParSet *pPar) {
  return kTRUE;
}

Int_t FairDetParDbIo::write(FairParSet *pPar) {
  return 0;
}
