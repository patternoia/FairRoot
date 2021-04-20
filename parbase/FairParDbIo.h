/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRPARDBIO_H
#define FAIRPARDBIO_H

#include "FairParIo.h"

class FairRtdbRun;

class FairParDbIo : public FairParIo
{
  public:
    FairParDbIo();
    virtual ~FairParDbIo();
    FairParDbIo(const FairParDbIo&) = delete;
    FairParDbIo& operator=(const FairParDbIo&) = delete;

    virtual void close();
    virtual void print();
    virtual void readVersions(FairRtdbRun*);
    virtual Bool_t check() { return kTRUE; };
    virtual void cd() { ; }

    void SetServerURI(std::string value);
    void SetAccessToken(std::string value);
    void SetVerbose(bool verbose = true);

    uint GetRunId() { return fRunId; };

  protected:
    std::string fServerURI {""};
    std::string fAccessToken {""};
    bool fVerbose {false};
    uint fRunId {0};

    ClassDef(FairParDbIo,0)
};

#endif /* FAIRPARDBIO_H */
