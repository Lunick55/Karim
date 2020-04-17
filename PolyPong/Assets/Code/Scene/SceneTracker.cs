using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SceneTracker : MonoBehaviour
{
    private Stack<SceneInfo> mSceneHistory = new Stack<SceneInfo>();
    
    //private void Awake()
    //{
    //    InitSceneSwitcher();
    //}
    //
    //private void InitSceneSwitcher()
    //{
    //    for (int i = 0; i < SceneManager.sceneCount; ++i)
    //    {
    //        Scene openScene = SceneManager.GetSceneAt(i);
    //        
    //        if (openScene.name == SceneInfoList.SCENE_SWITCHER.sceneID)
    //        {
    //            return;
    //        }
    //    }
    //    
    //    LoadSceneAsync(SceneInfoList.SCENE_SWITCHER);
    //}
    
    public AsyncOperation LoadSceneAsync(
        SceneInfo info, LoadSceneMode mode = LoadSceneMode.Additive, 
        Func<AsyncOperation, IEnumerator> loadHandler = null)
    {
        if (info.sceneType == SceneType.FULLSCREEN)
        {
            Debug.Log(string.Format("Adding fullscreen scene: {0} to history.", info.sceneID));
            mSceneHistory.Push(info);
        }

        AsyncOperation loadOperation = SceneManager.LoadSceneAsync(info.sceneID, mode);
        
        if (loadHandler != null)
        {
            StartCoroutine(loadHandler(loadOperation));
        }
        
        return loadOperation;
    }
    
    public AsyncOperation UnloadSceneAsync(
        string sceneID, Func<AsyncOperation, IEnumerator> unloadHandler)
    {
        AsyncOperation unloadOperation = SceneManager.UnloadSceneAsync(sceneID, 
            UnloadSceneOptions.UnloadAllEmbeddedSceneObjects);
        
        Debug.Log(string.Format("Unloading scene with id: {0} to history.", sceneID));
        
        StartCoroutine(unloadHandler(unloadOperation));
        return unloadOperation;
    }
}
