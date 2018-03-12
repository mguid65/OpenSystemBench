
BenchBuilder::BenchBuilder(){}
BenchBuilder::BenchBuilder(bool *config_) {
    if(config[0]) {
        algList.push_back(new NBody());
    }
    else {
        if(config[2]) {
            algList.push_back(new NBody());
        }
        if(config[3]) {
            algList.push_back(nullptr);
        }
    }
}
Algorithm * BenchBuilder::getAlgList() {

}
void runBench() {

}

void createStandardBench() {

}
