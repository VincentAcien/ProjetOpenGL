#version 300 es

precision mediump float;

in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec2 vTexCoords; // Coordonnées de texture du sommet

//uniform sampler2D uTexture;
uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;
uniform vec3 uLighDir_vs;
uniform vec3 uLightIntensity;

out vec3 fColor;

vec3 blinnPhong(){
    normalize(uLightDir_vs);
    w0 = -vPosition_vs;
    normalize(w0);
    fColor = uLightIntensity*(uKd*dot(uLightDir_vs,N)+uKs((w0+uLightDir_vs)/2*N)^uShininess;
}

void main(){
    vec4 sortie = texture(uTexture, vTexCoords);
    fColor = vec3(sortie);
    //normalize(vNormal_vs);
    //fColor = vNormal_vs;
}
