using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TestDLL : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        AndrickPlugin.AddNumToManagerStringA(5);
        AndrickPlugin.AddNumToManagerStringB(3);
        Debug.Log(AndrickPlugin.PrintManagerString());
        AndrickPlugin.AddNumToManagerStringA(5);
        Debug.Log(AndrickPlugin.PrintManagerString());

    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
