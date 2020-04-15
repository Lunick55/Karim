using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class ProgressBar : MonoBehaviour
{
    public static readonly float MAX_LOAD_VALUE = 0.9f;
    private SceneInfo mPrevSceneInfo;
    
    public virtual IEnumerator UpdateProgressBar(AsyncOperation loadOperation)
    {
        while (!loadOperation.isDone)
        {
            float progress = loadOperation.progress / MAX_LOAD_VALUE;
            Debug.Log(string.Format("Progress: {0}", progress));
            yield return null;
        }
    }
}
