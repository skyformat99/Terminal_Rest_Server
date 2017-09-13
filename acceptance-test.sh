#!/bin/bash

echo "Running Acceptance Tests"

./a.out &
PID="$?"

curl -vsko- -XGET "http://localhost:8088/"

curl -vsko- -XPOST --data "{\"cardType\": [\"Visa\",\"MasterCard\",\"EFTPOS\"],\"transactionType\": [\"Cheque\",\"Savings\",\"Credit\"]}" "http://localhost:8088/"

kill $PID