# CS465 Full Stack Development

## Compare and contrast the types of frontend development you used in your full stack project, including Express HTML, JavaScript, and the single-page application (SPA).

Express is a server-side framework that is meant for web applications and APIs. With it we were able to leverage handlebars to build out quick pages and partials to keep things neat. With JavaScript there was tons of flexibility and power to manipulate our HTML and CSS. Personally I enjoyed the SPA the most with its dynamic pages and the ability to make one page feel like an entire application. Trouble shooting an SPA was also a lot easier as it refreshed as you made changes which made my life a little easier. 

## Why did the backend use a NoSQL MongoDB database?

Flexibility and expansion. If the project is looking to grow and their is no set structured schema for the project, you're better going off with a NoSQL DB. There is also the consideration of better overall performance compared to traditional dbs. 

## How is JSON different from Javascript and how does JSON tie together the frontend and backend development pieces?

JSON uses key value pairs to store information and keeps only simple data types. JavaScript is more robust and expansive. JSON is considered one of the best languages to communicate between systems. It is designed to be lightweight, readable and easy to take as input. In this project all of the DB calls were returned to the application as JSON and we would parse through the information to display what we needed. 

## Provide instances in the full stack process when you refactored code to improve functionality and efficiencies, and name the benefits that come from reusable user interface (UI) components.

Breaking apart large HTML chunks makes it easier to read and understand. A good example is creating partials out of the header and footer. You can take something that could be 60+ lines of code on a monolithic page and cut it down to just a few lines. Sure the majority of it gets shipped to another location/file but it becomes easy to understand with proper naming conventions and commenting. This means someone else can pick up the code and run with it. 

## Methods for request and retrieval necessitate various types of API testing of endpoints, in addition to the difficulties of testing with added layers of security. Explain your understanding of methods, endpoints, and security in a full stack application.

Methods allow us to take in parameters and pass along arguements (if needed.) It allows us to massage data to where we need it within the applications. End points are the routes we end at. Some can be user login pages, or registrations. Others can be hidden maintenance pages ready to go up when needed. They both play a big role in security where together routes are guarded by validation methods and failsafes that are implemented. 

## How has this course helped you in reaching your professional goals? What skills have you learned, developed, or mastered in this course to help you become a more marketable candidate in your career field?

I have a deeper understanding of full stack development thanks to this course. It has helped me bring up questions I never thought to ask and given me the experience of creating a working website with several facets. I am a big believer in taking in as much knowledge as possible and will always be a forever student. 