package com.narwhale.name_todolist;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Adapter;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.List;

import static android.view.View.*;

public class MainActivity extends AppCompatActivity
{
    // lab 14 todo list

    ArrayList<String> taskList;
    ListView mTaskListView;
    Button addButton;
    Button deleteButton;
    EditText editText;
    ArrayAdapter<String> adapter;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        taskList = new ArrayList<String>();
        addButton = findViewById(R.id.add_button);
        deleteButton = findViewById(R.id.delete_button);
        editText = findViewById(R.id.textInputEditText);
        mTaskListView = findViewById(R.id.list_todo);

        adapter=new ArrayAdapter<String>(this,
                android.R.layout.simple_list_item_1,
                taskList);
        mTaskListView.setAdapter(adapter);

        addButton.setOnClickListener(new OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                taskList.add(editText.getText().toString());
                adapter.notifyDataSetChanged();
            }
        });
        deleteButton.setOnClickListener(new OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                taskList.remove(editText.getText().toString());
                adapter.notifyDataSetChanged();
            }
        });
    }
}
