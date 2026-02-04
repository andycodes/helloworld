package com.example.mybutton

import android.os.Bundle
import android.util.Log
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.material3.Button

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            MySimpleButton()
        }
    }
}

@Composable
fun MySimpleButton() {
    Button(onClick = {
        // 点击事件处理逻辑
        println("Button clicked!")
        Log.d("MainActivity", "Button clicked fansaihua!")
    }) {
        Text("点击我")
    }
}

@Preview(showBackground = true)
@Composable
fun PreviewButton() {
    MySimpleButton()
}
