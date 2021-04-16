void test_readdb() {
    auto *fRun = new FairRunAna();
    fRun->SetOutputFile("out.root");
    fRun->Init();

    FairRuntimeDb* rtdb = fRun->GetRuntimeDb();

    FairParDbIo* parIn = new FairParDbIo();
    rtdb->setFirstInput(parIn);

    FairParSet* par = rtdb->getContainer("FairBaseParSet");
    par->Dump();
    rtdb->initContainers(fRun->GetRunId());
    par->Dump();
    par->setChanged(kTRUE);

    FairParRootFileIo* parOut = new FairParRootFileIo(kTRUE);
    parOut->open("par.root");
    rtdb->setOutput(parOut);

    rtdb->saveOutput();
    rtdb->print();
}