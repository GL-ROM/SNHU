package com.example.project_three;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class HomePage extends AppCompatActivity {

    Button addEntry;
    TextView userData;
    EditText username, password;
    DBHelper DB;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_home_page);

        username = (EditText) findViewById(R.id.usernameLogin);
        password = (EditText) findViewById((R.id.passwordLogin));
        addEntry = (Button) findViewById(R.id.buttonAddEntry);
        DB = new DBHelper(this);

    }
}