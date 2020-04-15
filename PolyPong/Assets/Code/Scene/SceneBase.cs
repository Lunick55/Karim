using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SceneBase : MonoBehaviour
{
    private static GameObject instance;

    protected void Awake()
    {
        if (!instance)
        {
            instance = Instantiate(Resources.Load<GameObject>("Prefab/Persistent/POLY_PONG_CORE"));
            instance.name = "POLY_PONG_CORE";
            
            SceneTracker sceneTracker = instance.GetComponent<SceneTracker>();
            sceneTracker.LoadSceneAsync(SceneInfoList.CAMERA_MANAGER);
            
            //instance.GetComponent<SceneTracker>().LoadSceneAsync(SceneInfoList.SCENE_SWITCHER);
        }
    }
}
