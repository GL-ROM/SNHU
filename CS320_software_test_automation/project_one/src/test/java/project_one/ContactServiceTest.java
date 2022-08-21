// Gabriel Romero
// 6-1 Project One

package project_one;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.Test;

public class ContactServiceTest {

	@Test
	public void testContactService() {
		ContactService cs = new ContactService();
		Contact c1 = new Contact("1234567890", "Gabriel", "Romero", "7185551234", "123-45 105th Road New York");
		Contact c2 = new Contact("0987654321", "John", "Doe", "7187771234", "23-45 10th Road New York");
		Contact c3 = new Contact("5432167890", "Gabriel", "Romero", "6465551234", "43-55 155th Road New York");
		assertTrue(cs.add(c1));
		assertTrue(cs.add(c2));
		assertTrue(cs.add(c3));
		}
	
	@Test
	public void updateFirstName() {
		ContactService cs = new ContactService();
		Contact c1 = new Contact("1234567890", "Gabriel", "Romero", "7185551234", "123-45 105th Road New York");
		cs.add(c1);
		cs.updateFirstName(c1, "Derek");
		assertEquals("Derek", c1.getFirstName());
	}
	
	@Test
	public void updateLastName() {
		ContactService cs = new ContactService();
		Contact c1 = new Contact("1234567890", "Gabriel", "Romero", "7185551234", "123-45 105th Road New York");
		cs.add(c1);
		cs.updateLastName(c1, "Joe");
		assertEquals("Joe", c1.getLastName());
	}
	
	@Test
	public void updatePhoneNumber() {
		ContactService cs = new ContactService();
		Contact c1 = new Contact("1234567890", "Gabriel", "Romero", "7185551234", "123-45 105th Road New York");
		cs.add(c1);
		cs.updatePhoneNumber(c1, "7775558888");
		assertEquals("7775558888", c1.getPhoneNumber());
	}
	
	@Test
	public void updateAddress() {
		ContactService cs = new ContactService();
		Contact c1 = new Contact("1234567890", "Gabriel", "Romero", "7185551234", "123-45 105th Road New York");
		cs.add(c1);
		cs.updateAddress(c1, "456 Main Street Anywhere USA");
		assertEquals("456 Main Street Anywhere USA", c1.getAddress());
	}
}
		



