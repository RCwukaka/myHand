var jq = jQuery.noConflict();
var transmitterIcon;// //////ң������ͼ��
var trasimageImg;// ///ң����ԭ��ͼ��
var room;// //////////////���ң������Ӧ�ķ����
var trasname;// //////////ң��������
var stateString = "able";// //////state״̬
var roomimage;// ////���ң������Ӧ�ķ���ͼ��
var dataInfo = new Array(5);// ///////ң������ʱ����Ϣ
var newtrasname;
var change=false;

// ////////�õ�ң����������
function gettransmittername() {
	var tras = window.location.toString();
	trasimageImg = tras.split("=")[4];
	var trasname_hehe = tras.split("=")[3];
	trasname = trasname_hehe.split("&")[0];
	var roomparama = tras.split("=")[1];
	room = roomparama.split("&")[0];
	var roomimageparama = tras.split("=")[2];
	roomimage = roomimageparama.split("&")[0];
	jq("#transmitterIcon").attr("src", "./images/" + trasimageImg); // ///////��ʼ��ң����ͼƬ
	jq("#TransmitterName").val(trasname);
}

function back() {
	window.location.assign("transmitterlist.html?room=" + room + "&roomimage="
			+ roomimage);
}

// /////////////ʱ��ѡ������
jq(function() {
	gettransmittername();

	jq(".transmitterIcon").on("click", function() {
		transmitterIcon = jq(this).attr("src");
		jq("img").removeClass("tapreflectafter");
		jq(this).addClass("tapreflectafter");
	});
	jq("#Iconsure").click(function() {
		jq("#transmitterIcon").attr("src", transmitterIcon);
	});

	// //////////////////////////
	if(trasname!="trans"){
	// ////////���ع���ͨ��0��Ĭ��ֵ
		backchannel(room,trasname,0,true);
	}
});
function backchannel(room,trasname,channel,state){
	jq.ajax({
		type : "GET",
		url : "/smartHome",
		data : "action=212&readtransmitter=02&roomname=" + room + "&trasname="
				+ trasname+"&channel="+channel,
		dataType : "text",
		success : function(data) {
			data = data.replace(/(^\s*)|(\s*$)/g, "");
			if (data != "") {
				dataInfo = data.split("&");
				for (var i = 0; i < dataInfo.length; i++) {
					dataInfo[i] = dataInfo[i].split("=")[1];
				}
				dataInfo[4]=checkchannel(channel);
				if (parseInt(dataInfo[3]) == 0) {
					stateString = "disable";
				}else{
					stateString="able";
				}
				scroll(dataInfo,state,stateString);					
			} else {
				alert("ң����������!!!");
			}
		}
	});
}

function setchannel(room,trasname,channel,hour,minute,workday,state){
	
	jq.ajax({
		type : "GET",
		url : "/smartHome",
		data : "action=202&roomname="+room+"&trasname="+trasname+"&channel="+channel
		+"&hour="+hour+"&minute="+minute+"&workday="+workday+"&state="+state,
		dataType : "text",
		success : function(data) {			
		}
	});
}

function channelcheck(channel){
	var check=["ͨ��1��",
	           "ͨ��1�ر�",
	           "ͨ��2��",
	           "ͨ��2�ر�",
	           "ͨ��3��",
	           "ͨ��3�ر�",
	           "ͨ��4��",
	           "ͨ��4�ر�",
	           "ͨ��5��",
			   "ͨ��5�ر�",
			   "ͨ��6��",
			   "ͨ��6�ر�",
			   "ͨ��7��",
			   "ͨ��7�ر�",
			   "ͨ��8��",
			   "ͨ��8�ر�"];
	for(var i=0;i<check.length;i++){
		if(check[i]==channel){
			channel=i;
			break;
		};
	}
	return channel;
}

function checkchannel(channel){
	var check=["ͨ��1��/",
	           "ͨ��1�ر�/",
	           "ͨ��2��/",
	           "ͨ��2�ر�/",
	           "ͨ��3��/",
	           "ͨ��3�ر�/",
	           "ͨ��4��/",
	           "ͨ��4�ر�/",
	           "ͨ��5��/",
			   "ͨ��5�ر�/",
			   "ͨ��6��/",
			   "ͨ��6�ر�/",
			   "ͨ��7��/",
			   "ͨ��7�ر�/",
			   "ͨ��8��/",
			   "ͨ��8�ر�/"];
	return check[channel];
}

var mermory="ͨ��1��";
function scroll(dataInfo,aa,stateString) {
	var optOne = {
		theme : 'sense-ui', // Ƥ����ʽ
		display : 'modal', // ��ʾ��ʽ
		mode : 'scroller', // ����ѡ��ģʽ
		stepMinute : 1,
		cancelText : "OK",
		lang : 'zh',
		onChange:function(valueText, inst){
			if(valueText.split("/")[0]!=mermory){
				backchannel(room,newtrasname,channelcheck(valueText.split("/")[0]),false);
				mermory=valueText.split("/")[0];
			}		
		},
		onSelect:function(valueText, inst){
			inst.show();
			var hour_param=valueText.split("/")[1];
			var hour=hour_param.split(":")[0]+":";
			var minute_param=valueText.split("/")[1];
			var minute=minute_param.split(":")[1];
			var workday=valueText.split("/")[2];				
			setchannel(room,newtrasname,channelcheck(valueText.split("/")[0]),hour,minute,workday,stateString);
		},
		button3 : state,
		button3Text : stateString,
		rows : 5,
		wheels : [ {
			"ͨ��" : {				
				"ͨ��1��/" : "1/UP",
				"ͨ��1�ر�/" : "1/DN",
				"ͨ��2��/" : "2/UP",
				"ͨ��2�ر�/" : "2/DN",
				"ͨ��3��/" : "3/UP",
				"ͨ��3�ر�/" : "3/DN",
				"ͨ��4��/" : "4/UP",
				"ͨ��4�ر�/" : "4/DN",
				"ͨ��5��/" : "5/UP",
				"ͨ��5�ر�/" : "5/DN",
				"ͨ��6��/" : "6/UP",
				"ͨ��6�ر�/" : "6/DN",
				"ͨ��7��/" : "7/UP",
				"ͨ��7�ر�/" : "7/DN",
				"ͨ��8��/" : "8/UP",
				"ͨ��8�ر�/" : "8/DN"
			},
			"Сʱ" : {
				"--:":"--",
				"0:" : "0��",
				"1:" : "1��",
				"2:" : "2��",
				"3:" : "3��",
				"4:" : "4��",
				"5:" : "5��",
				"6:" : "6��",
				"7:" : "7��",
				"8:" : "8��",
				"9:" : "9��",
				"10:" : "10��",
				"11:" : "11��",
				"12:" : "12��",
				"13:" : "13��",
				"14:" : "14��",
				"15:" : "15��",
				"16:" : "16��",
				"17:" : "17��",
				"18:" : "18��",
				"19:" : "19��",
				"20:" : "20��",
				"21:" : "21��",
				"22:" : "22��",
				"23:" : "23��"
			},
			"����" : {
				"--":"--",
				"0" : "00",
				"1" : "01",
				"2" : "02",
				"3" : "03",
				"4" : "04",
				"5" : "05",
				"6" : "06",
				"7" : "07",
				"8" : "08",
				"9" : "09",
				"10" : "10",
				"11" : "11",
				"12" : "12",
				"13" : "13",
				"14" : "14",
				"15" : "15",
				"16" : "16",
				"17" : "17",
				"18" : "18",
				"19" : "19",
				"20" : "20",
				"21" : "21",
				"22" : "22",
				"23" : "23",
				"24" : "24",
				"25" : "25",
				"26" : "26",
				"27" : "27",
				"28" : "28",
				"29" : "29",
				"30" : "30",
				"31" : "31",
				"32" : "32",
				"33" : "33",
				"34" : "34",
				"35" : "35",
				"36" : "36",
				"37" : "37",
				"38" : "38",
				"39" : "39",
				"40" : "40",
				"41" : "41",
				"42" : "42",
				"43" : "43",
				"44" : "44",
				"45" : "45",
				"46" : "46",
				"47" : "47",
				"48" : "48",
				"49" : "49",
				"50" : "15",
				"51" : "51",
				"52" : "52",
				"53" : "53",
				"54" : "54",
				"55" : "55",
				"56" : "56",
				"57" : "57",
				"58" : "58",
				"59" : "59"
			},
			"������" : {
				"/--":"--",
				"/Mon" : "Mon",
				"/Tue" : "Tue",
				"/Wed" : "Wed",
				"/Thr" : "Thr",
				"/Fir" : "Fir",
				"/Sat" : "Sat",
				"/Sun" : "Sun",
				"/Mon,Wed,Fir" : "Mon,Wed,Fir",
				"/Tue,Thr,Sat" : "Tue,Thr,Sat",
				"/Workday" : "Workday",
				"/Holiday" : "Holiday"
			},
		} ]
	};
	if(aa==true){
		jq('#scroller').mobiscroll('init', optOne);
		jq('#scroller').mobiscroll('setValue',
				[ dataInfo[4], dataInfo[0], dataInfo[1], dataInfo[2]], true, 1);
	}else{
		jq('#scroller').mobiscroll("destroy");
		jq('#scroller').mobiscroll('init', optOne);
		jq('#scroller').mobiscroll('setValue',
				[ dataInfo[4], dataInfo[0], dataInfo[1], dataInfo[2]], true, 1);
		jq('#scroller').mobiscroll("show");
	}
}

function state(){
		if (jq(this).html() == "able") {
			jq(this).html("disable");
			stateString = "disable";
		} else {
			jq(this).html("able");
			stateString = "able";
		}
}
// ////////////����ң����
function saveTransmitter(trasname, transmitterIcon) {
	if (trasname != "") {
		if (trasname.length <= 10) {
			if (trasname != "trans") {
				content = "action=201&roomname=" + room + "&trasname="
						+ trasname + "&trasimage=" + transmitterIcon;
				jq.ajax({
					type : "GET",
					url : "/smartHome",
					data : content,
					dataType : "text",
					success : function(data) {
						var state = data.replace(/(^\s*)|(\s*$)/g, "");
						if (state == "1") {
							alert("����ɹ�����");
							backchannel(room,trasname,0);
						} else if (state == "0") {
							alert("�������������");
						}
					}
				});
			} else {
				alert("ң������������Ϊtrans��������");
			}
		} else {
			alert("ң���������ȳ������Ƶ�10�ַ����ȣ�������");
		}
	} else {
		alert("ң����������Ϊ�գ���");
	}
}

// //////////////�޸�ң������Ϣ��ÿ�η���newtrasname->�·����� trasname->�ɷ�����...���ֱ��ȫ������
function changetransmitterinfo(trasname, newtrasname, transmitterIcon) {
	if (newtrasname != "") {
		if (newtrasname.length <= 10) {
			if (newtrasname != "trans") {
				content = "action=220&roomname=" + room + "&trasname=" + trasname 
				+ "&newtrasname="+ newtrasname + "&newtrasimage="+ transmitterIcon ;
				jq.ajax({
					type : "GET",
					url : "/smartHome",
					data : content,
					dataType : "text",
					success : function(data) {
						var state = data.replace(/(^\s*)|(\s*$)/g, "");
						if (state == "1") {
							alert("�޸ĳɹ�����");
							backchannel(room,newtrasname,0);
						} else if (state == "0") {
							alert("�޸ĳ���������");
						} else if (state == "2") {
							alert("�����������������޸�ң�������ƣ�");
						}
					}
				});
			} else {
				alert("ң������������Ϊtrans��������");
			}
		} else {
			alert("ң���������ȳ������Ƶ�10�ַ����ȣ�������");
		}
	} else {
		alert("ң����������Ϊ�գ���");
	}
}

// ////////����ң������Ϣ�Ĳ�ͬ�����޸Ļ��߱������
function changeable() {
	transmitterIcon = jq("#transmitterIcon").attr("src").split("/")[2];
	newtrasname = document.getElementById("TransmitterName").value;
	if (trasname == "trans") {
		saveTransmitter(newtrasname, transmitterIcon);
	} else {
		if (newtrasname == trasname && transmitterIcon == trasimageImg) {
			if (change) {
				changetransmitterinfo(trasname, newtrasname, transmitterIcon);
			} else {
				saveTransmitter(newtrasname, transmitterIcon);
			}
		} else {
			changetransmitterinfo(trasname, newtrasname, transmitterIcon);
		}
	}
}
