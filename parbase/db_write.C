{
    FairRuntimeDb* rtdb = FairRuntimeDb::instance();
    rtdb->addRun(123);

    FairBaseParSet* par=dynamic_cast<FairBaseParSet*>(rtdb->getContainer("FairBaseParSet"));
    assert(par->hasChanged() == kFALSE);
    assert(par->getInputVersion(0) == -1);
    assert(par->getInputVersion(1) == -1);
    assert(par->getInputVersion(2) == -1);

    par->SetBeamMom(321);
    par->setChanged();

    FairParDbIo* parOut = new FairParDbIo();
    parOut->SetVerbose(kTRUE);
    parOut->SetServerURI("http://tgb_php_1:8008");
    parOut->SetAccessToken("test");
    TGenBase::Client::Instance()->PostRequest("Admin", "Truncate", R"({"ModelName": "ObjectStore"})");


    rtdb->setOutput(parOut);
    rtdb->saveOutput();
    rtdb->print();
}