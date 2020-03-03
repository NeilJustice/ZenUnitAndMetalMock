set -eux

if [ "$CODE_COV_MODE" == "ON" ];
then
  lcov --directory . --capture --output-file coverage.info
  lcov --list coverage.info
  bash <(curl -s https://codecov.io/bash) -f coverage.info || echo "Codecov did not collect coverage reports"
fi
