using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using System.Text;

public class ServerControlPanel : MonoBehaviour
{
    public TextMeshProUGUI UserCountText;
    public TextMeshProUGUI UserNamesText;

    public void Start()
    {
        
    }

    public void Update()
    {
        UserCountText.text = string.Format("{0} / {1}", AndrickPlugin.GetConnectedUserCount(), AndrickPlugin.GetMaxUserCount());
        //GetUsernames();
    }

    //private void GetUsernames()
    //{
    //    StringBuilder sb = new StringBuilder(AndrickPlugin.GetMaxUserCount() * 64);
    //    AndrickPlugin.GetUsernames(sb, sb.Capacity);
    //
    //    UserCountText.text = sb.ToString();
    //}
    //
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
