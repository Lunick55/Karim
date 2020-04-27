using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TitleScene : SceneBase<TitleScene>
{
    public void OnCreateServerPressed()
    {
        Persistent.Instance.GetComponent<SceneTracker>().LoadSceneSynchronously(SceneInfoList.CREATE_SERVER);
    }

    public void OnJoinServerPressed()
    {
        Persistent.Instance.GetComponent<SceneTracker>().LoadSceneSynchronously(SceneInfoList.JOIN_SERVER);
    }
}
