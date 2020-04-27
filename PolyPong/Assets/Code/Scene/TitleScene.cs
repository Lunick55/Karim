using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TitleScene : SceneBase<TitleScene>
{
    public void OnCreateServerPressed() { GetSceneTracker().LoadSceneSynchronously(SceneInfoList.CREATE_SERVER); }
    public void OnJoinServerPressed() { GetSceneTracker().LoadSceneSynchronously(SceneInfoList.JOIN_SERVER); }
}
