{
    gSystem->Unlink("par.root");

    FairRuntimeDb* rtdb = FairRuntimeDb::instance();
    rtdb->addRun(123);

    FairParDbIo* parIn = new FairParDbIo();
    parIn->SetVerbose(kTRUE);
    parIn->SetServerURI("http://tgb_php_1:8008");
    parIn->SetAccessToken("test");

    rtdb->setFirstInput(parIn);

    FairParRootFileIo* parOut = new FairParRootFileIo(kTRUE);
    parOut->open("par.root");
    rtdb->setOutput(parOut);

    FairBaseParSet* par=dynamic_cast<FairBaseParSet*>(rtdb->getContainer("FairBaseParSet"));
    // par->setInputVersion(1, 0);

    // fRun->Init();

    rtdb->getCurrentRun()->print();
    rtdb->setInputVersion(123, (Text_t*)"FairBaseParSet", 1, 0);
    rtdb->setInputVersion(123, (Text_t*)"FairBaseParSet", 1, 1);
    rtdb->setInputVersion(123, (Text_t*)"FairBaseParSet", 1, 2);

    rtdb->getCurrentRun()->print();
    rtdb->initContainers(123);

    // FairBaseParSet* par=dynamic_cast<FairBaseParSet*>(rtdb->getContainer("FairBaseParSet"));
    // par->setInputVersion(1, 0);
    // rtdb->getCurrentRun()->print();
    assert(par->GetBeamMom() == 321);
    par->Dump();
    par->setChanged(kTRUE);

    rtdb->saveOutput();
    rtdb->print();
}