var jq = jQuery.noConflict();
var roomname;
var roomimage;
function getroomInfo() { ////////�����õ�roomname��roomimage����
	var room = window.location.toString();
	roomname = room.split("=")[1].split("&")[0];
	roomimage=room.split("=")[2];
}
jq(function(){
	getroomInfo();
	jq(".ui-title").text(roomname);	
	jq("#info").prepend("<li><a style='vertical-align: middle; line-height: 60px;'><img src='./images/"
			+ roomimage
			+ "'style='width:50%'>"
			+ roomname + "</a></li>");
	jq("#info").listview("refresh");
	jq.ajax({
		type : "GET",
		url : "/smartHome",
		data : "action=210&readtransmitter=01&roomname=" + roomname, /////////////roomnameΪ��ֵ������
		dataType : "text",
		success : function(data) {
			transmitterAll = data;
			transmitterAll = transmitterAll.split("=")[1];
			roommessage(transmitterAll);
		}
	});
});
/////////////����ң������ѯ����Ϣ
function roommessage(transmitterAll) {
	var a = 1;
	var number=parseInt(transmitterAll)+1;
	for (var i = 1; i < number; i++) {
		jq.ajax({
					type : "GET",
					url : "/smartHome",
					data : "action=211&readtransmitter=00&roomname="
							+ roomname + "&time=" + a,
					dataType : "text",
					success : function(data) {
						var transmitter = data.split("&")[0];
						var transmittername = transmitter.split("=")[1];
						var transmitterparama = data.split("&")[1];
						var transmitterIcon = transmitterparama.split("=")[1];
						html = "<li><a style='vertical-align: middle; line-height: 60px;'><img src='./images/"
								+ transmitterIcon
								+ "'style='width:50%'><div style='display:block;float:left'>"
								+ transmittername + "</div></a></li>";
						jq("#info").append(html);
						jq("#info").listview("refresh");
						
						
						////////����transmitterIcon��������ͬ���豸
						/////////����Ϊ���������豸
						//jq("ul li:last").find("a").append("<input type='range'  data-highlight='true' value='25'min='0'max='100'/>").trigger('create');
						//jq("input[type='number']").css("display","none");
						//jq(".ui-slider-track:last").css("top","15px");
						
						
						////////����Ϊ�л��������͵��豸
						jq(".ui-btn-text:last").find("a").append('<select name="switch" id="switch" data-role="slider"><option value="on">On</option><option value="off" >Off</option></select>').trigger('create');
						jq("input[type='number']").css("display","none");
						jq(".ui-slider-track:last").css("top","15px");
						//////////����Ϊ�����豸
						
												
					}
				});
		a++;
	};
};

function back(){
	window.location.assign("index.html");
}