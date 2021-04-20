/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGENERICPARDBIO_H
#define FAIRGENERICPARDBIO_H

#include "FairDetParDbIo.h"

class FairParSet;
class FairRtdbRun;

class FairGenericParDbIo : public FairDetParIo
{
  public:
    FairGenericParDbIo(FairParDbIo* parIo);
    ~FairGenericParDbIo() {}
    virtual Bool_t init(FairParSet*);
    virtual Bool_t read(FairParSet*);
    virtual Int_t write(FairParSet*);
    Int_t findInputVersion(Text_t *name);

  protected:
    FairParDbIo* fParIo{nullptr};

    ClassDef(FairGenericParDbIo,0)
};

#endif /* FAIRGENERICPARDBIO_H */
