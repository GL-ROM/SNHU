// Gabriel Romero
// 6-1 Project One

package project_one;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.Test;

public class ContactTest {

	@Test
	public void testContact() {
		Contact contact = new Contact("1234567890", "Gabriel", "Romero", "7185551234", "123-45 105th Road New York");
		assertTrue(contact.getContactId().equals("1234567890"));
		assertTrue(contact.getFirstName().equals("Gabriel"));
		assertTrue(contact.getLastName().equals("Romero"));
		assertTrue(contact.getPhoneNumber().equals("7185551234"));
		assertTrue(contact.getAddress().equals("123-45 105th Road New York"));
	}

	@Test
	public void testContactIdIsNull() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Contact(null, "Gabriel", "Romero", "7185551234", "123-45 105th Road New York");
		}); 
	}
	
	@Test
	public void testFirstNameIsNull() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Contact("1234567890", null, "Romero", "7185551234", "123-45 105th Road New York");
		}); 
	}
	
	@Test
	public void testLastNameIsNull() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Contact("1234567890", "Gabriel", null, "7185551234", "123-45 105th Road New York");
		}); 
	}
	
	@Test
	public void testPhoneNumberIsNull() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Contact("1234567890", "Gabriel", "Romero", null, "123-45 105th Road New York");
		}); 
	}
	
	@Test
	public void testAddressIsNull() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Contact("1234567890", "Gabriel", "Romero", "7185551234", null);
		}); 
	}
	
	@Test
	public void testContactIdTooLong() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Contact("12345678905", "Gabriel", "Romero", "7185551234", "123-45 105th Road New York");
		}); 
	}
	
	@Test
	public void testFirstNameTooLong() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Contact("1234567890", "Gabriellellelle", "Romero", "7185551234", "123-45 105th Road New York");
		}); 
	}
	
	@Test
	public void testLastNameTooLong() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Contact("1234567890", "Gabriel", "Romerororororo", "7185551234", "123-45 105th Road New York");
		}); 
	}
	
	@Test
	public void testPhoneNumberTooLong() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Contact("1234567890", "Gabriel", "Romero", "71855512345", "123-45 105th Road New York");
		}); 
	}
	
	@Test
	public void testAddressTooLong() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Contact("1234567890", "Gabriel", "Romero", "7185551234", "123-45 105th Road New York New York 11151-1141");
		}); 
	}
	
}

