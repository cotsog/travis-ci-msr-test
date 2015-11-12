# travis-ci-msr-test
This project is only a test to check whether the virtual machines of Travis-CI support MSR accesses. They do, but only for a small subset of the commonly available MSRs. Consequently, we cannot use Travis-CI to test LIKWID's functionality as it tries to access not supported MSRs.
