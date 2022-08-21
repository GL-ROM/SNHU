package com.example.project_three;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class LoginActivity extends AppCompatActivity {

    EditText username, password;
    Button buttonLogin;
    DBHelper DB;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        username = (EditText) findViewById(R.id.usernameLogin);
        password = (EditText) findViewById((R.id.passwordLogin));
        buttonLogin = (Button) findViewById(R.id.buttonLogin);
        DB = new DBHelper(this);

        buttonLogin.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String user = username.getText().toString();
                String pass = password.getText().toString();

                if (user.equals("") || pass.equals("")) {
                    Toast.makeText(LoginActivity.this, "Please Enter All Fields.", Toast.LENGTH_SHORT).show();
                } else {
                    Boolean checkUserPass = DB.checkUsernamePassword(user, pass);
                    if (checkUserPass == true) {
                        Toast.makeText(LoginActivity.this, "Signin Successful", Toast.LENGTH_SHORT).show();
                        Intent intent = new Intent(getApplicationContext(), HomePage.class);
                        startActivity(intent);
                    } else {
                        Toast.makeText(LoginActivity.this, "Invalid Credentials", Toast.LENGTH_SHORT).show();
                    }
                }
            }
        });
    }
}