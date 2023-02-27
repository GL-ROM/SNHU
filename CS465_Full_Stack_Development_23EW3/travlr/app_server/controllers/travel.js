const request = require('request');
const apiOptions = {
    server: 'http://localhost:3000'
}

/* RENDER Travel List View */
const renderTravelList = (req,res, responseBody) => {
    let message = null;
    let pageTitle = process.env.npm_package_description + ' - Travel';
    if (!(responseBody instanceof Array)) {
      message = "API Lookup Error";
      responseBody = [];
    } else {
      if(!responseBody.length) {
        message = "No trips exist in database!";
      }
    }

    res.render('travel', {
      title: pageTitle,
      trips: responseBody,
      message
    });
};

/* GET travel View */
const travelList = (req, res) => {
    const path = '/api/trips';
    const requestOptions = {
        url: `${apiOptions.server}${path}`,
        method: 'GET',
        json: {},
    };

    console.info('>> travelController.travelList calling ' + requestOptions.url);

    request(
        requestOptions,
        (err, { statusCode }, body) => {
          if (err) {    
            console.error(err);
          }
          renderTravelList(req, res, body);
        }
    );
};
const travel = (req, res) => {
  res.render('travel', { title: 'Travlr Getaways', trips});
};

module.exports = {
  travelList
};