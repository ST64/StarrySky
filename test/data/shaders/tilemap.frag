#version 330
in vec2 texposition;
out vec4 outColor;
uniform sampler2D tex;
void main(){
	outColor = texture(tex, texposition);
	if (outColor.a == 0.0){
		discard;
	}
}
