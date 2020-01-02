#version 150
in vec2 Texcoord;
out vec4 outColor;
uniform sampler2D tex;
void main(){
	outColor = texture(tex,Texcoord);
	if (outColor.a == 0.0){
		discard;
	}
} 
