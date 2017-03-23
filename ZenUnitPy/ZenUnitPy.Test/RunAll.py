import sys
import nose

noseConfig = nose.config.Config()
noseConfig.testMatchPat = 'Tests|_test'
noseConfig.verbosity = 3
sys.exit(0 if nose.run(config=noseConfig) else 1)
