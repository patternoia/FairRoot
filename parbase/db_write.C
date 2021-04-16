{
    TGenBase::Client::Instance()->SetVerbose();
    TGenBase::Client::Instance()->PostRequest("Admin", "Truncate", R"({"ModelName": "ObjectStore"})");
    auto *fRun = new FairRunAna();
    // fRun->SetOutputFile("out.root");
    fRun->Init();

    FairRuntimeDb* rtdb = fRun->GetRuntimeDb();

    FairBaseParSet* par=dynamic_cast<FairBaseParSet*>(rtdb->getContainer("FairBaseParSet"));
    assert(par->hasChanged() == kFALSE);
    assert(par->getInputVersion(0) == -1);
    assert(par->getInputVersion(1) == -1);
    assert(par->getInputVersion(2) == -1);
    par->setChanged();

    FairParDbIo* parOut = new FairParDbIo();
    rtdb->setOutput(parOut);
    rtdb->saveOutput();
    rtdb->print();
}