const RUSSIA = {
  hasLegalSystem(bribe) {
    return false;
  },
};

const USA = {
  hasLegalSystem() {
    return true;
  },
};


RUSSIA.hasLegalSystem(1);
