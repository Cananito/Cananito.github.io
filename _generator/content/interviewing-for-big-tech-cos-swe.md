% title: Interviewing For Big Tech Companies (Software Engineering)
% generate_footer

# Interviewing For Big Tech Companies (Software Engineering)

Given that interviewing for software engineering roles in big tech companies is a skill of its own, **the goal of this document** is solely to help people gain or improve that skill and increase their chances of getting a job at a big tech company. It does not argue for or against the interview process and neither does it propose something better.

## General Preparation

### Big O Notation

Not always, but in most interview exercises/problems you’ll be asked to identify the time/runtime or space/memory complexity of a method or algorithm. Be familiar with both the [notation and their name](https://en.wikipedia.org/wiki/Big_O_notation#Orders_of_common_functions). Mainly:

* O(1) = constant.
* O(log n) = logarithmic.
* O(n) = linear.
* O(n^2) = quadratic.
* O(c^n) = exponential.

This will be asked with one of three purposes:

* The interviewer simply wants to assess you have the skill to correctly identify complexity.
* You presented more than one solution and the interviewer wants you to go with the most optimal.
* Your solution is not as optimal as the interviewer expects, so once you identify the complexity, they’ll tell you what’s the complexity of the solution they expect from you.

### Basic Data Structures

* Hash Map/Table (A.K.A. Dictionary).
* Linked List (singly and doubly).
* Queue.
* Stack.
* Set.

You won’t necessarily be asked to implement these, but you’ll very likely be using them as part of your solutions. So it’s very important you’re very familiar with them: how they’re implemented, and the runtime complexity of all their operations (read, add, remove, etc.).

### Binary Trees

* Implementation (modeling it).
* Traversals: pre, in, post.
* Depth-First Search.
* Inserting.
* Runtime complexity of all operations.

Less important, but be familiar with:

* Breadth-First Search.
* Deleting.
* Balancing.

### Algorithm Techniques/Methods

* Recursion.
* Dynamic Programming.

### Other Topics

These are either less likely to come up or just need to have a notion about them:

* Sorting algorithms: Extremely unlikely you’ll need to implement one. They’ll likely come up in conversation only when you sort something via standard library methods in order to assess your runtime complexity identification skills of a given solution.
* Trees: Mainly for modeling. Outside of that, might be useful to be aware/familiar with some concrete types of trees:
    * Binary tree.
    * Ternary tree.
    * N-ary tree.
    * Binary search tree.
    * B-tree.
    * AVL tree.
    * Red-black tree.
    * B-tree.
    * Trie.
* Threading/locking/async: Interviewers might add this aspect to their problem to test knowledge around it.
* Binary search on both binary trees and arrays: Also unlikely for you to have to code it up, but will be useful to know how it’s done.
* Bitmasks and bitwise operations: These tend to show up in tricky questions (which are likely banned from most companies) that involve performance.
* Heaps and priority queues: // TODO.
* Graphs: // TODO. Outside of that, might be useful to be aware/familiar with some concrete types of graphs:
    * Directed graph.
    * Undirected graph.
    * Directed acyclic (DAG).
* ArrayDeque (A.K.A./and/or: Circular Buffer, Ring Buffer, ArrayQueue): Will probably never come up, but they’re interesting! (For iOS folks, NSMutableArray is [implemented this way](http://ciechanowski.me/blog/2014/03/05/exposing-nsmutablearray/), which is why inserting and removing objects at index 0 is super fast!)

### Whiteboard

This is optional, but because onsite interviews will very likely be on a whiteboard, it’s recommended that you practice solving problems in one. If you’re not used to writing code in one, odds are it’ll hurt you a tiny bit since you’ll either run out of space, write extremely slow, find yourself erasing a lot, trying to fit stuff you missed in tight spaces, etc.

A few tips are:

* Start at the very top left or as close as you can get to that corner.
* Do not write things down as they come to your mind. Quite the opposite, try to have a rough draft of the whole code in your head before writing it down. This will save you from erasing or doing weird contortions in order to fit missing code.
* Use a right corner for non-code, like input and output examples.

## Domain Specific Preparation

### iOS with Objective-C

* Memory management.
    * How ARC works.
    * How ARC compares to garbage collection.
    * Ownership property attributes: `strong`, `weak`, `assign` (with both objects and primitives), `copy`, etc.
    * How to prevent memory leaks: retain cycles via property ownership attributes and block scope capturing.
* Delegates, notification center, target/action, KVO, responder chain, handler/callback blocks.
* Copying.
    * NSCopying protocol: `- copyWithZone:`.
    * NSMutableCopying protocol: `-mutableCopyWithZone:`.
    * NSObject class: `- copy` and `- mutableCopy`.
* Equality.
    * NSObject protocol: `- isEqual:` and `- hash`.
    * NSObject class: default implementation of that protocol.
* Block syntax. Some companies/interviewers will require you to know it, some others are a bit more forgiving/flexible. So just to be safe, memorize [goshdarnblocksyntax.com](http://goshdarnblocksyntax.com/).
* Extending classes via categories (and/or class extensions) vs subclassing.

### iOS with Swift

TODO: Need to update with latest language features!

* [Memory management](https://developer.apple.com/library/content/documentation/Swift/Conceptual/Swift_Programming_Language/AutomaticReferenceCounting.html).
    * How ARC works.
    * How ARC compares to garbage collection.
    * `weak` and `unowned` references.
    * How to prevent memory leaks: retain cycles via property ownership (solved with `weak` or `unowned` references) and closure scope capturing (solved with closure capture lists).
* Reference vs value semantics: classes, structs, `inout`.
* Optionals, [optional binding](https://developer.apple.com/library/prerelease/content/documentation/Swift/Conceptual/Swift_Programming_Language/TheBasics.html#//apple_ref/doc/uid/TP40014097-CH5-ID333), and [optional chaining](https://developer.apple.com/library/content/documentation/Swift/Conceptual/Swift_Programming_Language/OptionalChaining.html).
* Enums: `indirect` ([recursive enumerations](https://developer.apple.com/library/content/documentation/Swift/Conceptual/Swift_Programming_Language/Enumerations.html#//apple_ref/doc/uid/TP40014097-CH12-ID536)), [raw values](https://developer.apple.com/library/content/documentation/Swift/Conceptual/Swift_Programming_Language/Enumerations.html#//apple_ref/doc/uid/TP40014097-CH12-ID149), and [associated values](https://developer.apple.com/library/content/documentation/Swift/Conceptual/Swift_Programming_Language/Enumerations.html#//apple_ref/doc/uid/TP40014097-CH12-ID148).
* Generics: [type parameters](https://developer.apple.com/library/content/documentation/Swift/Conceptual/Swift_Programming_Language/Generics.html#//apple_ref/doc/uid/TP40014097-CH26-ID182) and [associated types](https://developer.apple.com/library/content/documentation/Swift/Conceptual/Swift_Programming_Language/Generics.html#//apple_ref/doc/uid/TP40014097-CH26-ID189).
* [Type casting](https://developer.apple.com/library/content/documentation/Swift/Conceptual/Swift_Programming_Language/TypeCasting.html) (checking types and downcasting).
* [Optional protocol requirements](https://developer.apple.com/library/content/documentation/Swift/Conceptual/Swift_Programming_Language/Protocols.html#//apple_ref/doc/uid/TP40014097-CH25-ID284).
* [Access control levels](https://developer.apple.com/library/content/documentation/Swift/Conceptual/Swift_Programming_Language/AccessControl.html#//apple_ref/doc/uid/TP40014097-CH41-ID5): `open`, `public`, `internal`, `fileprivate`, `private`.
* The [guard](https://developer.apple.com/library/content/documentation/Swift/Conceptual/Swift_Programming_Language/Statements.html#//apple_ref/doc/uid/TP40014097-CH33-ID524) branch statement.
* Closure syntax. Some companies/interviewers will require you to know it, some others are a bit more forgiving/flexible. So just to be safe, memorize [goshdarnclosuresyntax.com](http://goshdarnclosuresyntax.com/).
* Extending classes via class extensions vs subclassing.

### Android

TODO!

### Front End

TODO!

### Back End

TODO!

## The Interview

### Choosing a Language

It’s very likely you’ll have a choice on which language to use. Always pick the one you’re most familiar with or know the best.

That said, there are a few things to consider:

* If it’s not a popular one, odds are your recruiter won’t find interviewers that are familiar with it, and your odds of succeeding may be lower since interviewers not familiar with it won’t be able to make as good of an assessment.
* If you’re interviewing for an iOS or Android role but you’re not very familiar with Objective-C/Swift or Java (respectively), you should still stick to your main language. It’ll make it a bit harder or error-prone for the recruiter to find the correct interviewers, but the odds of you succeeding will likely be higher.
* If you’re interviewing for an iOS role and the language you’re familiar the most is Objective-C, it’s tempting to choose a less verbose one because it’ll take less whiteboard space. It’s highly suggested you stick to Objective-C.

### Syntax Errors

Most companies are forgiving when it comes to syntax errors (Facebook might be the most strict). That said, you should strive to avoid them and write code that essentially compiles.

### Interviewer Notes

Interviewers both take notes and copy your code. For note taking they’ll either use their computer or pen and paper (although some with great memory don’t take notes). For the copy of your code though, they’ll either type it live into their computer or take pictures of the whiteboard and then transcribe it all into their computers once the interview is over.

Many times the interviewers that write your code live into their computers won’t tell you about it at the beginning, so it throws people off sometimes: it’s either distracting or it makes it feel like they’re not paying attention. With that said, know that they _are_ paying attention (which may make it less distracting).

### Before The Problem(s)

The first 3-10 minutes of the interview are likely for the interviewer to ask you domain specific questions, behavioral questions, about your resume, or to answer any questions you have about the company or the interviewer’s job (this last one is most likely to happen at the end of the interview).

### The Problem(s)

The key to performing well in the interview is communication and verbalizing most—if not all—of your thoughts.

The other thing you should keep in mind is that in most—if not all cases—you want to have a working solution fully coded, rather than a highly optimized solution that’s incomplete or contains many errors.

The following steps are a good recipe to succeed:

TI = The interviewer.  
Y = You.

1. TI: They will describe the problem to you.
1. Y: Ask questions that clarify or reveal the specific edge cases of the problem. If the interviewer didn’t give you input examples, it might be a good idea to ask for some. If you don’t have any questions, at the very list verify that you understood the problem by saying out loud what you need to do. A few examples of questions: “do I have to worry about case sensitivity?”, “can you remind me of the definition of x?”, “can the input be a negative number?”, “is there a specific memory or runtime complexity I should aim for?”, etc.
1. Y: Once everything is cleared out, vaguely describe the first solution that comes to mind. If multiple solutions came to mind before or during your description of the first solution, continue by mentioning/describing them. If you gave more than one, tell the interviewer what are the pros and cons of each one and which one you’d like to go with.
1. TI: They might have a different opinion on what solution you should go with. Odds are they’re trying to guide you in the right direction, so it’s recommended you gracefully take their recommendation (after understanding and evaluating/assessing it, never take recommendations blindly!).
1. Y: Try and give them all the steps of the solution‘s implementation verbally. In some cases this is not feasible or very hard to do so, but try. In some cases the steps are simply the main lines of a method. In other cases the steps are a bit bigger, general, and/or abstract.
1. TI: If they detect an issue in your steps hopefully they’ll bring it up. They might also have new questions or suggestions for you. But at this stage it’s likely that not much conversation around the solution needs to take place anymore.
1. Y: Announce you’ll now proceed to write code and do so. If you can, speak and write at the same time. If this is hard, try doing the speaking before or after you write each line of code.</li>
1. Y: Once you’re done writing the code you needed to write, tell the interviewer: “I’m now going to test the code to see if it works. Do you have any question, comment, or suggestion before I do so?”. If they do have one, address it.
1. Y: (VERY IMPORTANT STEP!) Now proceed to test the code by making a line by line dry run<span style="color: #892bf5; font-weight: bold;">*</span> with a couple or few different inputs (if you were giving examples of them, use those) and going line by line of all the code you wrote. For example: “Ok let’s say we pass in 5, so x = 5, x square is 25, if x is greater than 10 we do this, then we return true. If we pass in 1, x = 1, x square is 1, if x is less than 10 we do this, we return false”.
1. Y: If you found errors or issues, address them. If not, tell the interviewer that is your solution.
1. TI: 3 things can happen now: they’ll add something new to the problem, they’ll give you a new problem, or you’re done with the interview. If it’s one of the first two, simply repeat from step 1.

<span style="color: #892bf5; font-weight: bold;">*</span> There are very few interviewers who’s expectation of testing the code isn’t a line by line dry run of your code, but to write actual unit tests. Make sure to ask the interviewer what are their expectations when it comes to testing the code.

### After The Problem(s)

You’ll likely get 5 minutes at the end of the interview to ask questions to the interviewer (if this didn’t happen at the beginning). For the most part (if not the sole purpose of) this is for you to genuinely learn about the company through the interviewer.

## Practicing and Other Resources

TODO: Links to coding challenge websites like LeetCode.

TODO: [Cracking the Coding Interview](https://www.amazon.com/Cracking-Coding-Interview-Programming-Questions/dp/0984782850) by Gayle Laakmann McDowell

TODO: [Cracking the Coding Interview videos](https://vimeo.com/ondemand/ctci)

## Specific Companies

### Google

TODO: Process (recruiter contact, schedule phone interview, schedule on-site interview, interviewers submit feedback, recruiter decides whether to send review packets to committee, committee makes a hiring decision, review packet is sent to Larry (or a VP?) for a quick last check, offer is extended).

TODO: Practice in a Google Doc for phone interview. Tools, Preferences..., Uncheck: “Automatically capitalize words” and “Use smart quotes”.

TODO: On-site: 5 interviews of 45 mins each. 1 hour for lunch with a Googler, free to ask anything, you don’t get evaluated.

TODO: Google Hiring Process videos:

* [How We Hire](https://www.youtube.com/watch?v=k-baHBzWe4k)
* [Prepare for a Google Engineering Interview](https://www.youtube.com/watch?v=ko-KkSmp-Lk)
* [Example Coding/Engineering Interview](https://www.youtube.com/watch?v=XKu_SEDAykw)

### Facebook

TODO!
