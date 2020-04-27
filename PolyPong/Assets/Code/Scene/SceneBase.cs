using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SceneBase<T> : Singleton<T> where T : Singleton<T>
{
    private static GameObject persistenceInstance;

    public void Awake()
    {
        if (!persistenceInstance)
        {
            if (!Persistent.Instance)
            {
                persistenceInstance = Instantiate(Resources.Load<GameObject>("Prefab/Persistent/POLY_PONG_CORE"));
                persistenceInstance.name = "POLY_PONG_CORE";
                Debug.Log("CREATING INSTANCE");
            }
            else
            {
                persistenceInstance = GameObject.Find("POLY_PONG_CORE");
            }
        }
    }

    public SceneTracker GetSceneTracker()
    {
        return Persistent.Instance.GetComponent<SceneTracker>();
    }

    public void SetScene(SceneInfo SceneID)
    {
        GetSceneTracker().LoadSceneSynchronously(SceneID);
    }

    private void ShutdownRakNet()
    {
        if (Persistent.Instance.IsCurrentUserTheServer())
        {
            if (AndrickPlugin.ShutdownServer())
            {
                Debug.Log("Successfully shutdown the server!");
            }
        }
        else
        {
            if (AndrickPlugin.ShutdownClient())
            {
                Debug.Log("Successfully shutdown the client!");
            }
        }
    }

    public void OnMainMenuPressed()
    {
        ShutdownRakNet();
        GetSceneTracker().LoadSceneSynchronously(SceneInfoList.TITLE_MENU);
    }

    public void OnQuitPressed()
    {
        Application.Quit();
    }

    private void OnApplicationQuit()
    {
        ShutdownRakNet();
    }
}
