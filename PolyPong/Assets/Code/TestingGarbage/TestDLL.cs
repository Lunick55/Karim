using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TestDLL : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        Debug.Log(AndrickPlugin.ActivateServer(5));
        Debug.Log(AndrickPlugin.TestMeDaddy());

    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
