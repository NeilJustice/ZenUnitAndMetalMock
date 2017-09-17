import sys
import nose
sys.path.append('..') # Jenkins

noseConfig = nose.config.Config()
noseConfig.testMatchPat = 'Tests|_test'
noseConfig.verbosity = 3
sys.exit(0 if nose.run(config=noseConfig) else 1)
