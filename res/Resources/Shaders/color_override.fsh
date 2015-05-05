uniform sampler2D texture;
uniform vec4 color;

void main()
{
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    gl_FragColor = vec4(color.rgb, pixel.a*color.a);
}