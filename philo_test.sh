#!/bin/bash

PHILO="./philo"
VALGRIND_LOG="valgrind.log"

# Function to run basic behavior test
basic_test_alive() {
    echo "🧪 Running basic alive behavior test..."
    $PHILO $1 $2 $3 $4 > output.txt &
    PHILO_PID=$!
    sleep 5
    kill $PHILO_PID
    grep "died" output.txt > /dev/null
    if [ $? -eq 1 ]; then
        echo "✅ Basic alive test passed: Philosopher did not die as expected."
    else
        echo "❌ Basic alive test filed: Philosopher died."
    fi
}

basic_test_dead() {
    echo "🧪 Running basic dead behavior test..."
    $PHILO $1 $2 $3 $4 > output.txt &
    PHILO_PID=$!
    sleep 10
    kill $PHILO_PID
    grep "died" output.txt > /dev/null
    if [ $? -eq 0 ]; then
        echo "✅ Basic dead test passed: Philosopher died as expected."
    else
        echo "❌ Basic dead test failed: Philosopher did not die."
    fi
}

basic_test_limit() {
    echo "🧪 Running basic limit behavior test..."
    $PHILO $1 $2 $3 $4 $5 > output.txt &
    PHILO_PID=$!
    sleep 5
    kill $PHILO_PID
    eating_count=$(grep "eating" output.txt | wc -l)
    expected_count=$(( $1 * $5 ))
    if [ "$eating_count" -eq "$expected_count" ]; then
        echo "✅ Basic limit test passed: Philosopher ate the expected number of times. \n Expected: $expected_count, Found: $eating_count"
    else
        echo "❌ Basic limit test failed: Philosopher did not eat the expected number of times."
    fi
}

# Function to run valgrind test
valgrind_test() {
    echo "🔍 Running Valgrind test for memory leaks..."
    valgrind --leak-check=full --show-leak-kinds=all --log-file=$VALGRIND_LOG $PHILO $1 $2 $3 $4 > /dev/null &
    PHILO_PID=$!
    sleep 5
    kill $PHILO_PID
    echo "📄 Valgrind log saved to $VALGRIND_LOG"
    grep "definitely lost" $VALGRIND_LOG
}

# Function to run with memory limit
memory_limit_test() {
    echo "🚧 Running with memory limit (10MB)..."
    ulimit -v 10240  # virtual memory limit in KB (10MB)
    $PHILO 5 800 200 200 > /dev/null &
    PHILO_PID=$!
    sleep 5
    kill $PHILO_PID
    echo "✅ Memory limited test done."
    # Reset ulimit
    ulimit -v unlimited
}

# Run tests
echo "🔧 Starting tests..."
# Basic test for alive philosophers
basic_test_alive 5 800 200 200
basic_test_alive 10 800 200 200
basic_test_alive 20 800 200 200
basic_test_alive 100 800 200 200
basic_test_alive 200 800 200 200
echo "✅ Basic test alive done."
rm output.txt
# Basic test for dead philosophers

basic_test_dead 5 800 200 200
basic_test_dead 10 800 200 200
basic_test_dead 20 800 200 200
basic_test_dead 100 800 200 200
basic_test_dead 200 800 200 200
echo "✅ Basic test dead done."
rm output.txt
#limited number of eating
basic_test_limit 5 800 200 200 3
basic_test_limit 10 800 200 200 2
basic_test_limit 20 800 200 200 7
basic_test_limit 100 800 200 200 5
basic_test_limit 200 800 200 200 3
echo "✅ Basic test limit done."
rm output.txt

# valgrind_test 5 800 200 200
# memory_limit_test

echo "🎉 All tests completed."