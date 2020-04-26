using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class ChatItem : MonoBehaviour
{
    public TextMeshProUGUI ChatItemText;

    public void PopulateMessage(string Message)
    {
        ChatItemText.text = string.Format(Message);
    }
}
