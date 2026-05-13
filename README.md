# Introduction
This is a [wordle game](https://en.wikipedia.org/wiki/Wordle) bot that solves the game using **Information Theory** more precisely using [entropy](https://www.geeksforgeeks.org/machine-learning/entropy-in-information-theory/) (entropy here does not pertain to Thermodynamic Entropy).

## How the bot works
### To understand the working of bot, let's first look at it from a larger view : 
1. Bot proposes the user a list of best possible 5-letter words to start the play.
2. Based on the word user enters, bot recalculates the best possible word list again.
3. This repeats until game is over(6 rounds) or bot predicts the target word early.

Since the word entropy will be used a lot here, in simple terms entropy of a word can be understood as more the value of entropy, more the word list(from where we choose the words) will be shortened if we use that word.
### Now, going deep into the working :
1. To produce the initial word ranking list, entropy of **each word** is calculated and list is arranged in the decreasing order of entropy.
2. To calculate the entropy for each word, following **Shanon's Entropy** Formula is used:
$$H(X)=−\sum_{x∈X}P(x) \log_{2}(P(x))$$
3. Since, a word can be of 5-letters only, and each letter can result out to Grey, Yellow or Green, thus there are only **243 patterns** possible for a single word.
4. So, we can trace out a **pattern distribution** a word against all other words, using that distribution to calculate the probability and eventually average   entropy.
5. Repeating this process for all almost 18k words, gives us the initial ranking list.

### What happen's when user chooses a word
1. Based on the word choosen and it's entropy, word list is halfed a number of times(basically $(1/2)^number_of_bits)$.
2. Now, bot uses the **target word** against each word to recalculate the entropy for each word, using the pattern distribution as discussed above.
3. Thus, if the odds play right bot will be able to solve the game before 6 rounds.

## Build the bot in your system
Ensure you have [CMake](https://cmake.org/download/) and a C++ compiler installed in your system .
Clone the repo and 
1. Generate the build directory
```code 
cmake -S . -B build
```
2. Compile the project
```code 
cmake --build build --config release
```
3. Run the executable
- on Linux/Mac OS
```
./build/wordle_bot
```
- on Windows
```
.\build\Release\wordle_bot.exe
```

## Performance of the bot 
To test it's performance, I tested all 18k words, each iteration using one of them as target and tracing out a distribution for the number of rounds it took to solve it.
Here's the Result-

Distribution of number of Rounds in successful game finish:

 1 : 0

 2 : 32

 3 : 486

 4 : 968

 5 : 533

 6 : 296

AVERAGE SCORE : 4.248380

## Reference
This project is referenced from [3blue 1brown](https://www.youtube.com/watch?v=v68zYyaEmEA).
Other references taken to understand the maths and queries are -
- Great Lecture on Basics of [Information theory](https://youtu.be/ScX2aBFyrVU?si=gRN6N8S_B0QFOFVo).
- StackOverFlow
- Gemini - to discuss overall workflow queries.

