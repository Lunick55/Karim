using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Persistent : MonoBehaviour
{
    private static GameObject instance;

    private void Awake()
    {
        if (!instance)
        {
            instance = gameObject;
            DontDestroyOnLoad(gameObject);
        }
        else
        {
            Destroy(gameObject);
        }
    }
}
