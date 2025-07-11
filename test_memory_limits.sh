#!/bin/bash

echo "=== TESTING MEMORY LIMITATION FIXES ==="
echo

echo "Test 1: Moderate memory limit (should work):"
echo "ulimit -v 100000 && timeout 5s ./philo 4 800 200 200"
echo

echo "Test 2: Tight memory limit (should fail gracefully and exit quickly):"
echo "ulimit -v 30000 && timeout 5s ./philo 20 800 200 200"
echo

echo "Test 3: Very tight memory limit (should fail gracefully and exit quickly):"
echo "ulimit -v 15000 && timeout 5s ./philo 10 800 200 200"
echo

echo "Test 4: Extreme memory limit (should fail gracefully and exit quickly):"
echo "ulimit -v 5000 && timeout 3s ./philo 5 800 200 200"
echo

echo "=== EXPECTED BEHAVIOR ==="
echo "- Tests 2, 3, 4 should print 'Error: Philosopher creation failed'"
echo "- They should exit within 1 second (not hang until timeout)"
echo "- No zombie processes or deadlocks"

echo
echo "=== HOW TO TEST ==="
echo "1. Run: make clean && make"
echo "2. Test each command above"
echo "3. Verify quick exit on failure"
