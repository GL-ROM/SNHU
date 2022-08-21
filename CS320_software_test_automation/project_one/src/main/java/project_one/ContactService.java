// Gabriel Romero
// Project One

package project_one;

import java.util.ArrayList;
import java.util.List;

public class ContactService {
	
	private List<Contact> contacts;
	
	public ContactService() {
		contacts = new ArrayList<Contact>();
	}
	
	public boolean add(Contact contact) {
		boolean alreadyPresent = false;
		for (Contact c : contacts) {
			if (c.equals(contact)) {
				alreadyPresent = true;
			}
		}
		if (!alreadyPresent) {
			contacts.add(contact);
			return true;
		} else {
			throw new IllegalArgumentException("Invalid Contact ID");
		}
	}
	
	public void addContact(String contactId, String firstName, String lastName, String phoneNumber, String address) {
		Contact contact = new Contact(contactId, firstName, lastName, phoneNumber, address);
		this.add(contact);
	}
	
	public boolean updateFirstName(Contact contact, String name) {
		boolean change = false;
		for (Contact c : contacts) {
			if (c.getContactId().equals(contact.getContactId())) {
				contact.setFirstName(name);
				change = true;
			}		
		}
		return change;
	}
	
	public boolean updateLastName(Contact contact, String name) {
		boolean change = false;
		for (Contact c : contacts) {
			if (c.getContactId().equals(contact.getContactId())) {
				c.setLastName(name);
				change = true;
			}		
		}
		return change;
	}
	
	public boolean updatePhoneNumber(Contact contact, String number) {
		boolean change = false;
		for (Contact c : contacts) {
			if (c.getContactId().equals(contact.getContactId())) {
				c.setPhoneNumber(number);
				change = true;
			}		
		}
		return change;
	}
	
	public boolean updateAddress(Contact contact, String address) {
		boolean change = false;
		for (Contact c : contacts) {
			if (c.getContactId().equals(contact.getContactId())) {
				c.setAddress(address);
				change = true;
			}		
		}
		return change;
	}
	
	
}
