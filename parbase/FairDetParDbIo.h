/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDETPARDBIO_H
#define FAIRDETPARDBIO_H

#include "FairDetParIo.h"

class FairParSet;
class FairParDbIo;

class FairDetParDbIo : public FairDetParIo
{
  public:
    FairDetParDbIo(FairParDbIo* parIo);
    virtual ~FairDetParDbIo() {;};
    FairDetParDbIo(const FairDetParDbIo&) = delete;
    FairDetParDbIo& operator=(const FairDetParDbIo&) = delete;

    virtual Bool_t read(FairParSet*);
    virtual Int_t write(FairParSet*);

  protected:
    FairParDbIo* fParIo{nullptr};

    ClassDef(FairDetParDbIo,0)
};

#endif /* FAIRDETPARDBIO_H */
