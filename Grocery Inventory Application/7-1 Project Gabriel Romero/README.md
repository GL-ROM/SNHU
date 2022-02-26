# Grocery Store Inventory Assignment 

### Summarize the project and what problem it was solving.
I was to make an application that took account of the days purchase for a grocery store, focused on thier produce. They wanted to get the numbers and see how to rearange their sections based on popularity. I was to take in a file, read the items off the list (which would be the items sold for the day), tally them and spit out an informative screen with the names accompanied by the amount. There was also an option to search for just one specific item and to display a historgraph showing off the amount visually. This last part was to be done by reading in a data file that contained the name and amount only of the produce. 

The main language used for this project was CPP with data handling done by Python. 

### What did you do particularly well?
I beleive I was able to sort most of the tasks into smaller modular pieces that I could test individually and put together rather effeciently. Each function had a set purpose and did not fully overlap with each other. They were distinct and consise. This enabled me to keep my main call down to one line.  

### Where could you enhance your code? How would these improvements make your code more efficient, secure, and so on?
I could focus on refactoring and cleaning up anything that wasnt DRY. This would help with clarity and readablility for those who are not familar with the code I wrote. I would also add better descriptors and perhaps a more indepth starter comment about the code itself. I find that anything that helps answer even the smallest question of the code is helpful to fresh eyes on it. 

### Which pieces of the code did you find most challenging to write, and how did you overcome this? What tools or resources are you adding to your support network?
I ran into some issues getting my python to interact with my cpp in the beginning. It just was not recognizing it and it become a never ending cycle of troubleshooting. What I ended up doing was taking a break and looking up how it is done properly. I referenced the guide provided in the course and went step by step to see if I had missed anything. I was eventually able to get it to work and repeated the steps a few more times to make sure I nailed it down. Eventually I got it working and was relieved. 

Another portion was the reading of the file data as there are so many ways to do it. I had to test a few ways to see what was the simplest way for me to get this data to where I wanted it. Experimentation is helpful when it comes to issues like these. 

### What skills from this project will be particularly transferable to other projects or course work?
Being able to leverage CPP and Python on the same project is a pretty important skill that will transfer well in my eyes. I believe taking advantage of the pros of both languages would be important if wanting to remain flexable. 


### How did you make this program maintainable, readable, and adaptable?
Modularized it. As stated before I was happy with how I was able to break down the needed tasks into methods and have it chain call which is easy to follow and understand. I also ensured to leave plenty of comments and information on what I was doing/trying to achieve with certain lines of code. The only thing that would need to happen is generalize the file name into looking at the specific directory instead of using the named file I did. Other than that I beleive it could be used anywhere simple counts are needed. 
