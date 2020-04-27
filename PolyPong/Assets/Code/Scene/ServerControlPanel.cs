using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using System.Text;

public class ServerControlPanel : SceneBase<TitleScene>
{
    public TextMeshProUGUI UserCountText;
    public TextMeshProUGUI UserNamesText;

    public void Update()
    {
        if (Persistent.Instance.isNetworkActive && Persistent.Instance.isServer)
        {
            AndrickPlugin.ProcessPackets();
            AndrickPlugin.ExecuteEvents();
            UserCountText.text = string.Format("{0} / {1}", AndrickPlugin.GetConnectedUserCount().ToString(), AndrickPlugin.GetMaxUserCount().ToString());
            GetUsernames();
            AndrickPlugin.SendPackets();
        }
    }

    private void GetUsernames()
    {
        StringBuilder sb = new StringBuilder(AndrickPlugin.GetMaxUserCount() * 64);
        AndrickPlugin.GetUsernames(sb, sb.Capacity);

        UserNamesText.text = sb.ToString();
    }
    
    //private string CleanseString(StringBuilder sb)
    //{
    //    string cleanString;
    //
    //    for (int i = 0; i < sb.Length; ++i)
    //    {
    //        if (sb[i] == '\0')
    //        {
    //            
    //        }
    //    }
    //}
}
