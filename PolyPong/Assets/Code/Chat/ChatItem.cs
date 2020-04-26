using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class ChatItem : MonoBehaviour
{
    public TextMeshProUGUI ChatItemText;

    public void PopulateMessage(string Username, string Message)
    {
        ChatItemText.text = string.Format("{0}: {1}", Username, Message);
    }
}
