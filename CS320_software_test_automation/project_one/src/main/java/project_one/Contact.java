// Gabriel Romero
// 6-1 Project one


package project_one;

public class Contact {
	
	// Fields for class
	private String contactId;
	private String firstName;
	private String lastName;
	private String phoneNumber;
	private String address;
	
	// Constructor
	public Contact(String contactId, String firstName, String lastName, String phoneNumber, String address) {
		if (contactId == null || contactId.length() > 10) {
			throw new IllegalArgumentException("Invalid Contact ID");
		}
		
		this.contactId = contactId;
		
		if (firstName == null || firstName.length() > 10) {
			throw new IllegalArgumentException("Invalid First Name");
		}
		
		this.firstName = firstName;
		
		if (lastName == null || lastName.length() > 10) {
			throw new IllegalArgumentException("Invalid Last Name");
		}
		
		this.lastName = lastName;
		
		if (phoneNumber == null || phoneNumber.length() != 10) {
			throw new IllegalArgumentException("Invalid Phone Number");
		}
		
		this.phoneNumber = phoneNumber;
		
		if (address == null || address.length() > 30) {
			throw new IllegalArgumentException("Invalide Address");
		}
		
		this.address = address;
	}
	
	// Setter Methods
	
	public void setContactId(String id) {
		this.contactId = id;
	}
	
	public void setFirstName(String name) {
		this.firstName = name;
	}
	
	public void setLastName(String name) {
		this.lastName = name;
	}
	
	public void setPhoneNumber(String number) {
		this.phoneNumber = number;	
	}
	
	public void setAddress(String address) {
		this.address = address;
	}
	
	// Getter Methods
	
	public String getContactId() {
		return this.contactId;
	}
	
	public String getFirstName() {
		return this.firstName;
	}
	
	public String getLastName() {
		return this.lastName;
	}
	
	public String getPhoneNumber() {
		return this.phoneNumber;
	}
	
	public String getAddress() {
		return this.address;
	}
  
}
