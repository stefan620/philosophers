#!/bin/bash

echo "=== COMPREHENSIVE FAILURE TESTING SCRIPT ==="
echo

echo "1. Testing Memory Leak Detection:"
echo "valgrind --leak-check=full ./philo 4 800 200 200 2"
echo

echo "2. Testing with Limited Memory (should fail gracefully):"
echo "ulimit -v 30000 && ./philo 50 600 100 100"
echo

echo "3. Testing Thread Safety with Helgrind:"
echo "valgrind --tool=helgrind ./philo 3 310 200 200"
echo

echo "4. Testing Race Conditions (death message timing):"
echo "./philo 2 200 100 100"
echo

echo "5. Testing Resource Cleanup on Early Exit:"
echo "timeout 2s ./philo 10 2000 200 200"
echo

echo "6. Testing Invalid Arguments:"
echo "./philo 0 800 200 200"
echo "./philo -1 800 200 200" 
echo "./philo 4 -800 200 200"
echo

echo "7. Testing Edge Cases:"
echo "./philo 1 800 200 200  # Single philosopher"
echo "./philo 200 600 100 100  # Many philosophers"
echo

echo "=== RUN THESE TESTS AFTER FIXING COMPILER ISSUE ==="
