// Gabriel Romero
// Project One

package project_one;

import java.util.Date;

public class Appointment {

	// Fields
	private String appointmentId;
	private Date appointmentDate;
	private String appointmentDescription;
	
	// Appointment Constructor
	public Appointment(String appointmentId, Date appointmentDate, String appointmentDescription) {
		if (appointmentId == null || appointmentId.length() > 10) {
			throw new IllegalArgumentException("Invalid Appointment ID");
		}
		
		this.appointmentId = appointmentId;
		
		if (appointmentDate == null || appointmentDate.before(new Date())) {
			throw new IllegalArgumentException("Invalid Appointment Date");
		}
		
		this.appointmentDate = appointmentDate;
		
		if (appointmentDescription == null || appointmentDescription.length() > 50) {
			throw new IllegalArgumentException("Invalid Appointment Description");
		}
		
		this.appointmentDescription = appointmentDescription;
	}
	
	// Setters
	// Since the service can only add appointments the validation will happen there
	// No setters needed on this side due to everything being done by constructor
	
	// Getters
	public String getAppointmentId() {
		return this.appointmentId;
	}
	
	public Date getAppointmentDate() {
		return this.appointmentDate;
	}
	
	public String getAppointmentDescription() {
		return this.appointmentDescription;
	}
}
