# Empora
command-line program that validates a US address against the following API and outputs either the corrected address or "Invalid Address"

I used two ways to solutions to compute the solution for the above solution.

Solution One:
used 'curl' library for HTTP request, since it's more efficient and has the capacity to handle less complexity.

Here's how to run the solution_one: 
1. Replace 'YOUR_API_KEY' in the code with your actual API key from SmartyStreets
2. Make sure to link the program with the libcurl library while compiling. EX- g++ program.cpp -lcurl -o program
3. Use the command-line program with your CSV file as input. Ex -  cat input.csv | ./program

Make sure to replace input.csv with the path to your actual CSV file. The program will read the addresses from the CSV file, validate them using the SmartyStreets API, and output the results.


Solution Two:
done without the 'curl' as I just wanted to see if I'm able to or not. I had to go bit of research and read some docs to gather the right way to solve it.

Here's how to run the solution_two:
1. Replace 'YOUR_API_KEY' in the code with your actual API key from SmartyStreets
2. Complie the program. Ex - g++ program.cpp -o program
3. Use the command-line program with your CSV file as input - cat input.csv | ./program

Make sure to replace input.csv with the path to your actual CSV file. The program will read the addresses from the CSV file, validate them using the SmartyStreets API, and output the results. 

