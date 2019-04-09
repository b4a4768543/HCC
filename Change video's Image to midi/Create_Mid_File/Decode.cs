using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Create_Mid_File
{
    class Decode
    {
        public Decode()
        {

        }

        string Decoding(int i)
        {
            string s = Convert.ToString(i + 9, 16); 
            return s;

        }
        //string Decoding()
        //{
        //    string s = "";
        //    switch(i)
        //    {
        //        case 0:
        //            s = "09";
        //            break;
        //        case 1:
        //            s = "0A";
        //            break;
        //        case 2:
        //            s = "0B";
        //            break;
        //        case 3:
        //            s = "0C";
        //            break;
        //        case 4:
        //            s = "0D";
        //            break;
        //        case 5:
        //            s = "0E";
        //            break;
        //        case 6:
        //            s = "0F";
        //            break;
        //        case 7:
        //            s = "10";
        //            break;
        //        case 8:
        //            s = "11";
        //            break;
        //        case 9:
        //            s = "12";
        //            break;
        //        case 10:
        //            s = "13";
        //            break;
        //        case 11:
        //            s = "14";
        //            break;
        //        case 12:
        //            s = "15";
        //            break;
        //        case 13:
        //            s = "16";
        //            break;
        //        case 14:
        //            s = "17";
        //            break;
        //        case 15:
        //            s = "18";
        //            break;
        //        case 16:
        //            s = "19";
        //            break;
        //        case 17:
        //            s = "";
        //            break;
        //        case 18:
        //            s = "";
        //            break;
        //        case 19:
        //            s = "";
        //            break;
        //        case 20:
        //            s = "09";
        //            break;
        //        case 21:
        //            s = "";
        //            break;
        //        case 22:
        //            s = "";
        //            break;
        //        case 23:
        //            s = "";
        //            break;
        //        case 24:
        //            s = "";
        //            break;
        //        case 25:
        //            s = "";
        //            break;
        //        case 26:
        //            s = "";
        //            break;
        //        case 27:
        //            s = "";
        //            break;
        //        case 28:
        //            s = "";
        //            break;
        //        case 29:
        //            s = "";
        //            break;
        //        case 30:
        //            s = "09";
        //            break;
        //        case 31:
        //            s = "";
        //            break;
        //        case 32:
        //            s = "";
        //            break;
        //        case 33:
        //            s = "";
        //            break;
        //        case 34:
        //            s = "";
        //            break;
        //        case 35:
        //            s = "";
        //            break;
        //        case 36:
        //            s = "";
        //            break;
        //        case 37:
        //            s = "";
        //            break;
        //        case 38:
        //            s = "";
        //            break;
        //        case 39:
        //            s = "";
        //            break;
        //        case 40:
        //            s = "09";
        //            break;
        //        case 41:
        //            s = "";
        //            break;
        //        case 42:
        //            s = "";
        //            break;
        //        case 43:
        //            s = "";
        //            break;
        //        case 44:
        //            s = "";
        //            break;
        //        case 45:
        //            s = "";
        //            break;
        //        case 46:
        //            s = "";
        //            break;
        //        case 47:
        //            s = "";
        //            break;
        //        case 48:
        //            s = "";
        //            break;
        //        case 49:
        //            s = "";
        //            break;
        //        case 50:
        //            s = "09";
        //            break;
        //        case 51:
        //            s = "";
        //            break;
        //        case 52:
        //            s = "";
        //            break;
        //        case 53:
        //            s = "";
        //            break;
        //        case 54:
        //            s = "";
        //            break;
        //        case 55:
        //            s = "";
        //            break;
        //        case 56:
        //            s = "";
        //            break;
        //        case 57:
        //            s = "";
        //            break;
        //        case 58:
        //            s = "";
        //            break;
        //        case 59:
        //            s = "";
        //            break;
        //        case 60:
        //            s = "09";
        //            break;
        //        case 61:
        //            s = "";
        //            break;
        //        case 62:
        //            s = "";
        //            break;
        //        case 63:
        //            s = "";
        //            break;
        //        case 64:
        //            s = "";
        //            break;
        //        case 65:
        //            s = "";
        //            break;
        //        case 66:
        //            s = "";
        //            break;
        //        case 67:
        //            s = "";
        //            break;
        //        case 68:
        //            s = "";
        //            break;
        //        case 69:
        //            s = "";
        //            break;
        //        case 70:
        //            s = "09";
        //            break;
        //        case 71:
        //            s = "";
        //            break;
        //        case 72:
        //            s = "";
        //            break;
        //        case 73:
        //            s = "";
        //            break;
        //        case 74:
        //            s = "";
        //            break;
        //        case 75:
        //            s = "";
        //            break;
        //        case 76:
        //            s = "";
        //            break;
        //        case 77:
        //            s = "";
        //            break;
        //        case 78:
        //            s = "";
        //            break;
        //        case 79:
        //            s = "";
        //            break;
        //        case 80:
        //            s = "09";
        //            break;
        //        case 81:
        //            s = "";
        //            break;
        //        case 82:
        //            s = "";
        //            break;
        //        case 83:
        //            s = "";
        //            break;
        //        case 84:
        //            s = "";
        //            break;
        //        case 85:
        //            s = "";
        //            break;
        //        case 86:
        //            s = "";
        //            break;
        //        case 87:
        //            s = "";
        //            break;
        //        default:
        //            break;
        //    }
        //    return s;
        //}
    }
}
