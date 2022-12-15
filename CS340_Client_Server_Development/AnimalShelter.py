from pymongo import MongoClient
from bson.json_util import dumps

class AnimalShelter(object):
    """ CRUD Operations for Animal collection in MongoDB """
    
    def __init__(self, username=None, password=None):
        #validate username and password was passed in
        if username and password:
            self.client = MongoClient('mongodb://%s:%s@localhost:56047' % (username, password), authSource='AAC')
        else:
            self.client = MongoClient('mongodb://localhost:56047')
        self.database = self.client['AAC']
        
        animals = self.database.animals
        
# json object converter. Takes in MongoDB cursor as arg.
    def convertToJSON(self, cursor):
        listCursor = list(cursor)
        return dumps(listCursor)
        
# Create Method for CRUD
    def create(self, data):
        if data is not None:
            insertData = self.database.animals.insert(data)
            if insertData!=0:
                print("True")
                return True
            else:
                print("False")
                return False
        else:
            raise Exception("Nothing to save, because data parameter is empty")
            
# Read Method for CRUD
    def read(self, search):
        results = self.database.animals.find(search, {"_id":False})
        if results.count() > 0:
            return results
        else:
            raise Exception("No records found")
        
    
# Update Method for CRUD
    def update(self, search=None, updates=None):
        if search and updates:
            updateDocument = self.database.animals.update( search, updates )
            return self.convertToJSON(updateDocument)
                
        else: 
            raise Exception("Update was unsuccessful")

# Delete Method for CRUD
    def delete(self, search=None):
        if search:
            deletedDocument = self.database.animals.delete_one( search )
            return self.convertToJSON(deletedDocument.raw_result
          
        else:
            raise Exception("Delete unsuccessful")
            
