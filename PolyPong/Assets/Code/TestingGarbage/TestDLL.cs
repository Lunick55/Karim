using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TestDLL : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        float[] quatBaby = new float[4];
        AndrickPlugin.CreateDefaultQuaternion(true, quatBaby);
        Debug.Log(quatBaby);
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
